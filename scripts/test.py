#! /usr/bin/env python

import sys
import os
import subprocess
import difflib
import re

def getBasePath(sas_plugin):
   """
   Get the path specific to the SAS installation
   """
   scriptPath = os.path.realpath(__file__)
   return scriptPath.replace("/scripts/test.py","")

def cleanOutput(specificPath,analyze_output):
   return analyze_output.replace(specificPath,"")

def printDiff(str1,str2):
   diff = difflib.ndiff(str1.splitlines(1), str2.splitlines(1))
   print ''.join(diff),

def runTest():
   cc, src, sas_plugin, checkers, refOutputName, environmentStr = sys.argv[1:]
   compile_env = {"SA_PLUGIN": sas_plugin, "SA_CHECKERS": checkers}
   compile_env.update(os.environ)

   #separate environment variable list by ';'
   if os.environ.has_key("PATH"):
      compile_env["PATH"] = os.environ["PATH"]
   environmentList = environmentStr.split(';')

   #get environment variable key-value pair
   for envStr in environmentList:
      env = envStr.split('=',1)
      if len(env) == 2:
         compile_env[env[0]] = env[1]
   basePath = getBasePath(sas_plugin)

   proc = subprocess.Popen([cc, "-c", "-std=c++11", src], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, env=compile_env)
   stdout, _ = proc.communicate()
   clean_analyzer_output = cleanOutput(basePath, stdout)

   refOutput = open(refOutputName).read()

   if refOutput.strip() == clean_analyzer_output.strip():
      return 0
   else:
      printDiff(refOutput,clean_analyzer_output)
      return 1

if __name__ == "__main__":
   exitCode = runTest()
   sys.exit(exitCode)
