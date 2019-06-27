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


test "PINA: 0x20, PINB: 0x30, PINC: 0x10 => PORTD: 0x00" 
setPINA 0x20 
setPINB 0x30
setPINC 0x10 
continue 3 
expectPORTD 0x00 
checkResult 

test "PINA: 0x05, PINB: 0x17, PINC: 0x30 => PORTD: 0x00" 
setPINA 0x05 
setPINB 0x17 
setPINC 0x30 
continue 3
expectPORTD 0x00 
checkResult 

test "PINA: 0x70, PINB: 0x50, PINC: 0x80 => PORTD: 0x01" 
setPINA 0x70 
setPINB 0x50 
setPINC 0x80 
continue 3 
expectPORTD 0x01 
checkResult 

test "PINA: 0x4F, PINB: 0x13, PINC: 0xC9 => PORTD: 0x03"   
setPINA 0x4F 
setPINB 0x13 
setPINC 0xC9 
continue 3 
expectPORTD 0x03 
checkResult





# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
