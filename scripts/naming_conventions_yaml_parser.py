'''
This is an experimental prototype that generates naming convention checkers from a .yaml file. Currently the templates
used to identify the object being checked are stored in /afs/cern.ch/user/d/daho/yaml/templates.

David Ho
August 2016
'''

import yaml
import argparse
import os
import datetime
import re

class ConventionReader(object):
    """Reader class"""
    def __init__(self, yamlfile):
        super(ConventionReader, self).__init__()
        self.yamlfile = yamlfile
        self.rules = {}
        self.project_name = ""
        self.known_clang_types= {
            "Function": "FunctionDecl",
            "Type": "TypeDecl",
            "TypeDef": "TypedefNameDecl",
            "ClassStructUnion": "CXXRecordDecl",
            "Enum": "EnumDecl",
            "Enumerator": "EnumConstantDecl",
            "DataMember": "FieldDecl",
            "Const": "VarDecl",
            "Namespace": "NamespaceDecl",
            "GlobalStatic": "VarDecl",
            "MemberStatic": "VarDecl",
            "LocalVariable": "VarDecl"
        }
        self.template_directory = "/afs/cern.ch/user/d/daho/SAS/templates/identifiers"
        self.identifiers = {}
        for file in os.listdir(self.template_directory):
            file_name, file_extension = os.path.splitext(file)
            if file_extension == ".template":
                template_name = os.path.splitext(file_name)[0]
                with open(os.path.join(self.template_directory, file), "r") as fobj:
                    self.identifiers[template_name] = fobj.read()
        with open("/afs/cern.ch/user/d/daho/SAS/templates/DefaultIdentifier.template", "r") as fobj:
            self.default_template = fobj.read()

    def check(self, convention_rules, object_name):
        # Are the required fields present?
        if not ("name" in convention_rules and "regex" in convention_rules and "description" in convention_rules):
            print("Required field 'name', 'regex' and/or 'description' not found; checker not written")
            return False
        name = convention_rules["name"]
        regex = convention_rules["regex"]
        # is the regex valid?
        try:
            re.compile(regex)
        except re.error as err:
            print(err)
            print("Regex error in {name}: {error}".format(name=name, error=err))
            return False
        # is there a known Clang type associated with the name?
        if object_name not in self.known_clang_types:
            if "clangType" in convention_rules:
                self.known_clang_types[object_name] = convention_rules["clangType"]
            else:
                print("Unable to find Clang type for '{name}'; checker not written".format(name=name))
                return False
        return True

    def read(self):
        with open(self.yamlfile, 'r') as yamlfile:
            content = yaml.load(yamlfile)
        if "project" in content:
            self.project_name = content["project"]["name"]
            self.project_author = content["project"]["author"]
        if "conventions" in content:
            conventions = content["conventions"]
            for object_name in conventions.keys():
                convention_rules = conventions[object_name]
                if self.check(convention_rules, object_name):
                    name = convention_rules["name"]
                    regex = convention_rules["regex"]
                    desc = convention_rules["description"]
                    clang_type = self.known_clang_types[object_name]
                    self.rules[object_name] = [name, regex, clang_type, desc]
                else:
                    continue
                if not object_name in self.identifiers.keys():
                    print("No identifier template found for '{name}'; using default template".format(name=name))
                    self.identifiers[object_name] = self.default_template


if __name__ == "__main__":
    argparser = argparse.ArgumentParser("convention creator", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    argparser.add_argument("file_name", type=str, help=".yaml file containing checker details")
    argparser.add_argument("destination", type=str, help="where the checker classes are generated")
    args = argparser.parse_args()

    year = datetime.date.today().strftime("%Y")
    reader = ConventionReader(args.file_name)
    reader.read()

    with open(os.path.join(args.destination, "CMakeLists.txt"), "w") as fobj:
        for name, attributes in reader.rules.iteritems():
            fobj.write("add_checker({name}Checker.cpp)\n".format(name=attributes[0]))

    for object_name, attributes in reader.rules.iteritems():
        convention_name = attributes[0]
        regex = attributes[1]
        clang_type = attributes[2]
        description = attributes[3]
        with open("/afs/cern.ch/user/d/daho/yaml/templates/CheckerBase.cpp.template", "r") as fobj:
            base_template = fobj.read()
        checker_code = base_template.format(author=reader.project_author,
            year=year,
            name=convention_name,
            project=reader.project_name,
            regex=regex,
            clang_type=clang_type,
            report_description=description,
            identifier_code=reader.identifiers[object_name])
        with open("/afs/cern.ch/user/d/daho/yaml/templates/CheckerHeader.h.template", "r") as fobj:
            header_template = fobj.read()
        header_code = header_template.format(author=reader.project_author,
            year=year,
            name=convention_name,
            name_caps=convention_name.upper(),
            project=reader.project_name,
            clang_type=clang_type,
            description=description)
        with open(os.path.join(args.destination, convention_name + "Checker.cpp"), "w") as fobj:
            fobj.write(checker_code)
        with open(os.path.join(args.destination, convention_name + "Checker.h"), "w") as fobj:
            fobj.write(header_code)
        print(convention_name + " checker created.")