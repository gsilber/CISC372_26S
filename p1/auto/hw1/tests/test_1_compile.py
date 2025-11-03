import unittest
from gradescope_utils.autograder_utils.decorators import weight
import subprocess32 as subprocess

class TestFiles(unittest.TestCase):
    @weight(30)
    def test_compile(self):
        """Check if source code compiles"""
        make = subprocess.Popen(["make","hw1"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        err = make.stderr.read().strip()
        make.terminate()
        referenceOutput = b""
        self.assertEqual(err, referenceOutput, "Source code does not compile!")
        print("Source code compiled successfully!")