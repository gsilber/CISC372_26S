import unittest
from gradescope_utils.autograder_utils.decorators import weight
import subprocess32 as subprocess
import os

class TestFiles(unittest.TestCase):
    @weight(30)
    def test_output(self):
        """Check if the output matches the reference output"""
        hw1 = subprocess.Popen(["./hw1"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output = hw1.stdout.read().strip()
        hw1.terminate
        output = os.linesep.join([s for s in output.decode().splitlines() if s])
        with open("hw1.out","rb") as outputFile:
            referenceOutput = outputFile.read().strip().decode()
        with open("hw1a.out","rb") as outputFile2:
            referenceOutput2 = outputFile2.read().strip().decode()
        self.assertEqual(output==referenceOutput or output==referenceOutput2, True, "The output of the program does not match the reference output!")
        print("The program output matches the reference output!")