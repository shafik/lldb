"""
Test lldb data formatter subsystem.
"""

from __future__ import print_function


import os
import time
import lldb
from lldbsuite.test.decorators import *
from lldbsuite.test.lldbtest import *
from lldbsuite.test import lldbutil


class LibcxxOptionalDataFormatterTestCase(TestBase):

    mydir = TestBase.compute_mydir(__file__)

    @add_test_categories(["libc++"])

    def test_with_run_command(self):
        """Test that that file and class static variables display correctly."""
        self.build()
        self.runCmd("file " + self.getBuildArtifact("a.out"), CURRENT_EXECUTABLE_SET)

        bkpt = self.target().FindBreakpointByID(
            lldbutil.run_break_set_by_source_regexp(
                self, "break here"))

        self.runCmd("run", RUN_SUCCEEDED)

        # The stop reason of the thread should be breakpoint.
        self.expect("thread list", STOPPED_DUE_TO_BREAKPOINT,
                    substrs=['stopped',
                             'stop reason = breakpoint'])

        # This is the function to remove the custom formats in order to have a
        # clean slate for the next test case.
        def cleanup():
            self.runCmd('type format clear', check=False)
            self.runCmd('type summary clear', check=False)
            self.runCmd('type filter clear', check=False)
            self.runCmd('type synth clear', check=False)
            self.runCmd(
                "settings set target.max-children-count 256",
                check=False)

        # Execute the cleanup function during test case tear down.
        self.addTearDownHook(cleanup)

        # empty vectors (and storage pointers SHOULD BOTH BE NULL..)
        self.expect("frame variable number",
                    substrs=['engaged=false'])

        lldbutil.continue_to_breakpoint(self.process(), bkpt)

        # first value added
        self.expect("frame variable number",
                    substrs=['engaged=true',
                             '[0] = 42',
                             '}'])

        # add some more data
        lldbutil.continue_to_breakpoint(self.process(), bkpt)

        self.expect("frame variable numbers",
                    substrs=['numbers =  engaged=false'])

        self.expect("p numbers",
                    substrs=['$0 =  engaged=false'])

        lldbutil.continue_to_breakpoint(self.process(), bkpt)

        self.expect("p numbers",
                    substrs=['$1 =  engaged=true {',
                             '[0] = size=4 {',
                               '[0] = 1',
                               '[1] = 2',
                               '[2] = 3',
                               '[3] = 4',
                               '}',
                             '}'])

        # add some more data
        lldbutil.continue_to_breakpoint(self.process(), bkpt)

        self.expect("frame variable ostring",
                    substrs=['ostring =  engaged=false'])

        lldbutil.continue_to_breakpoint(self.process(), bkpt)

        self.expect("p ostring",
                    substrs=['$2 =  engaged=true {',
                        '[0] = "hello"',
                        '}'])
