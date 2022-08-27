# 42-Exam__Rank02-Recursive-gnl-

This is my solution to the get_next_line problem of the 42 exam Rank-02.

The exam version of such problem is the equivalent of the mandatory-only part of the homonymous project of the 42cursus common-core.
For a detailed explanation of the problem you can read the [Subject.txt] present in this repo. (essentially, the problem is about reading files one line at the time).

**I solved this problem in a recursive fashion**. Executing this program against the [Tripouille tester]( https://github.com/Tripouille/gnlTester ) inside VS CODE's integrated terminal can show you some TIMEOUTS: **execute this program in your own machine's terminal and you'll be ok!**

# Explanation of my thought process.

1. [The fd_buffer structure](https://github.com/mmarinel/42-Exam__Rank02-Recursive-gnl-#the-fd_buffer-structure)
2. [The recursive algorithm](https://github.com/mmarinel/42-Exam__Rank02-Recursive-gnl-#the-recursive-algorithm)

## The fd_buffer structure
I decided to wrap my buffer inside a structure which has the following informations: 
- buf: the buffer
- buffer_size: the current buffer size
- offset: the offset inside the buffer--i.e.: where reading begins

As you can guess, storing the information about the buffer size implies it being not a constant in our code...it will be expanded and shrinked during execution as we will see shortly.

## The recursive algorithm
The idea can be condensed in the following 3 steps:
1. If offset is 0, this means the buffer is empty (we are either at the first call or we read all the characters inside of it during the previous one). So, we read the next buf_handle->buffer_size characters from the file and put them in our buffer.

2. We take the next line stored inside the buffer; if no line is present, or it ends where the buffer ends, we read everything there is inside the buffer starting from buf_handle->offset and store it in our variable (this will cause the offset to be set back to 0 because we read everything there was to read inside the buffer). If a new line is instead found and it doesn't end with the buffer, we update the offset to the next position after the end of the line we just found.

3. if offset is 0 and we didn't find a new line, that means we have to start all over again from point 1. Now, assuming the recursive call gives us the rest correctly, we just need to concatenate what we just read with the return of the recursive call (this is our *Inductive step*...if you will). Now, for the *base case*, if either offset is not 0 or we indeed found a new line, we just return what we read (the next line). In both cases, if either offset is 0 or it is at a position where a '\0' is present, we free the buffer and we set offset back to 0 beacause there is nothing more to read inside the buffer.
