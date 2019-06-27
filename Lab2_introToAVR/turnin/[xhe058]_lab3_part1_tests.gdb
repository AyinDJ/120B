# Test file for Lab2_introToAVR


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n


test "PINA: 0x20, PINB: 0x25 => PINC: 0x45" 
setPINA 0x20 
setPINB 0x25 
continue 3 
expectPORTC 0x45 
checkResult 

test "PINA: 0x01, PINB: 0x02 => PINC: 0x03"             
setPINA 0x01
setPINB 0x02
continue 3
expectPORTC 0x03
checkResult

test "PINA: 0x0F, PINB: 0x0F => PINC: 0x45"             
setPINA 0x0F
setPINB 0x0F
continue 3
expectPORTC 0x1E
checkResult

test "PINA: 0x1A, PINB: 0x2C => PINC: 0x46"             
setPINA 0x1A
setPINB 0x2C
continue 3
expectPORTC 0x46
checkResult

test "PINA: 0xA0, PINB: 0x01 => PINC: 0xA2"             
setPINA 0xA0
setPINB 0x01
continue 3
expectPORTC 0xA2
checkResult




# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
