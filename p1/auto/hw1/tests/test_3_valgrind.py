import unittest
from gradescope_utils.autograder_utils.decorators import weight
import subprocess32 as subprocess

class TestFiles(unittest.TestCase):
    @weight(20)
    def test_valgrind(self):
        """Check if there are memory leaks"""
        valgrind = subprocess.Popen(["valgrind","-s","./hw1"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output = valgrind.stderr.read().strip()
        valgrind.terminate()
        memory_leaks = b"All heap blocks were freed -- no leaks are possible" not in output
        memory_errors = b"ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)" not in output
        out_of_mem = b"Valgrind's memory management: out of memory" in output
        valgrind_passed = not memory_leaks and not memory_errors and not out_of_mem
        test = self.assertTrue(valgrind_passed, msg="Memory leaks detected!")
        print("No memory leaks detected!")