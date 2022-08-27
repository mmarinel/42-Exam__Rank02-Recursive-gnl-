# 42-Exam__Rank02-Recursive-gnl-

This is my solution to the get_next_line problem of the 42 exam Rank-02.

The exam version of such problem is the equivalent of the mandatory-only part of the homonymous project of the 42cursus common-core.
For a detailed explanation of the problem you can read the [Subject.txt] present in this repo. (essentially, the problem is about reading files one line at the time).

**I solved this problem in a recursive fashion**. Executing this program against the [Tripouille tester]( https://github.com/Tripouille/gnlTester ) inside VS CODE's integrated terminal may show you some TIMEOUTS: **execute this program in your own machine's terminal and you'll be ok!**

# Explanation of my thought process.

1. [The fd_buffer structure](https://github.com/mmarinel/42-Exam__Rank02-Recursive-gnl-#the-fd_buffer-structure)
2. [The recursive algorithm](https://github.com/mmarinel/42-Exam__Rank02-Recursive-gnl-#the-recursive-algorithm)
3. [The shrinking and expanding of the buffer size](https://github.com/mmarinel/42-Exam__Rank02-Recursive-gnl-#the-shrinking-and-expanding-of-the-buffer-size)

## The fd_buffer structure
I decided to wrap my buffer inside a structure which has the following informations: 
- buf: the buffer
- buffer_size: the current buffer size
- offset: the offset inside the buffer--i.e.: where reading begins

As you can guess, storing the information about the buffer size implies it being not a constant in our code...it will be expanded and shrinked during execution as we will see shortly.

The buffer is long buf_handle->buffer_size + 1 characters, always with a '\0' at the last position.

## The recursive algorithm
The idea can be condensed in the following 3 steps:
1. If offset is 0, this means the buffer is empty (we are either at the first call or we read all the characters inside of it during the previous one). So, we read the next buf_handle->buffer_size characters from the file and put them in our buffer.

2. We take the next line stored inside the buffer; if no line is present, or it ends where the buffer ends (this means where we encounter the first '\0' inside the buffer, which is not necessarily at the buf_handle->buffer_size index because the file can end before reading other buf_handle->buffer_size characters from it), we read everything there is inside the buffer starting from buf_handle->offset and store it in our variable (this will cause the offset to be set back to 0 because we read everything there was to read inside the buffer). If a new line is instead found and it doesn't end with the buffer, we update the offset to the next position after the end of the line we just found.

3. if offset is 0 and we didn't find a new line, that means we have to start all over again from point 1. Now, assuming the recursive call gives us the rest correctly, we just need to concatenate what we just read with the return of the recursive call (this is our *Inductive step*...if you will). Now, for the *base case*, if either there are no more characters to read from the file or we indeed found a new line, we just return what we read. In both cases, if either offset is 0 or it is at a position where a '\0' is present, we free the buffer and we set offset back to 0 beacause there is nothing more to read inside the buffer.

## The shrinking and expanding of the buffer size
Now, there is just one problem. As you may already know, the beauty of recursion (and the beauty of recursive code) comes with a cost, this cost being efficiency. There are cases where recursion can be an excellent solution to our problems and cases where the depth of the recursive calls can bear a significant overhead over our machine (each call adds a frame on the stack, and when we have too many calls we may even reach a stack overflow!).

So, how to make our get_next_line more efficient? Think about it for a second, what does it cause our function to call itself recursively? ...Gotcha!...The inability to store enough characters before the next new line is found!

So, a possible solution is this: whenever we are heading towards a next recursive call, we increase our buffer size by a **small** constant value so to decrease the probability of going recursively again with the next call!

Anyway, when we are done reading the next line, we may have reached a fairly big buffer size, and it is for this very reason that with every new call we reset our "true" buffer size with the value of the homonymous macro (BUFFER_SIZE) which we set to a default of 42.

This idea comes from the [TCP](https://en.wikipedia.org/wiki/Transmission_Control_Protocol) protocol. This protocol allows for a reliable transmission of data (i.e.: every packet is guaranteed to be received by the recipient and in the order it was sent with respect to all other packets).
One of the many things that TCP does is the so called "congestion control" [Rfc 5681](https://www.rfc-editor.org/rfc/rfc5681).
TCP regulates the sender's transmission speed according to the levels of congestion (i.e.: traffic) present inside the network (or, more precisely, along the path to the recipient).
If the sender detects low levels of congestion, it may decide to transmit at its maximum speed, otherwise it may be forced to send packets at a decreased speed (because sending them at the maximum possible speed may contribute to increase the levels of congestion even more, ultimately leading to a loss of packets which will have to be sent once again making the greater speed more inefficient than the lower one).

So, here you have it, the expanding and shrinking of a quantity to best fit the current conditions and reach the optimal level of efficiency!.
