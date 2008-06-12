" File: sum1.st 
	Purpose: sum positive integers problem
  Date: 10/3/97 
	Author: pc2@ecs.csus.edu  (laned)
	Source: smalltalk
	$Id: sumit.st,v 1.1 2005/03/06 05:13:57 laned Exp $ "
| v stream1 stream0 sum line |

(stream0 := CfsReadFileStream open: 'sumit.dat') isCfsError
	ifTrue: [^self error: stream0 message].
(stream1 := CfsWriteFileStream open: 'sum.out') isCfsError
	ifTrue: [^self error: stream1 message].

sum := 00.

[stream0 atEnd ]
   whileFalse: [
     line := stream0 nextLine.
      v := line asDecimal.
	v > 0 ifTrue: [ 	sum := sum + v asInteger ]
].

'The sum of positive integer is ' storeOn: stream1.
sum storeOn: stream1.
stream1 cr.

stream1 cr.

stream1 close.
stream0 close.
