# easyUtils
These are some utilites I developed while working on a bigger project.

These utilities were all designed to be easy to use and easy to maintain, with good performance.
The test and demo folders show their use.

They should work on all platforms, but only tested on Linux.

My design philosophy is to stay away from sharp edges. Some things that are IMHO overused are templates, pointers, and threads. As Sean Parent would say, my goal is to have none of these. Still sometimes it's best to dive into the deep end.


====

TextMap is a templated class that does constexpr text to integer mapping.

I wrote this to enable using a switch statement on a text value. See the last test case in test/textMapTest.cpp

This could not be done without templates and is an example of just how much can easily be done with them.

Thanks to @Pezo on stackoverflow for introducing me to deduction guides.

====

ThreadPool is a simple class for multithreading, another sharp edge.
 * It uses a single job queue for all threads.
 * The number of worker threads is defined on construction.
 * The intent is to have long running threads so that job setup time is a tiny fraction of total run time. A pipeline of subtasks is one way to accomplish this.

This implementation is basic and optimizations are definitely possible, but to date this has been quite sufficient for my needs.

Basic usage is this:
 * construct a ThreadPool.
 * use addJob() to add jobs to the queue.
 * call the ThreadPool() operator. This runs the jobs.
 * You may call addJob() at any time until you call finish().
 * call finish() to clean up and wait for the threads to end.

The size() method is provided in case you have to allocate a fraction of a resource, such as memory, per running thread.

nQueens in the demo folder is a brute force nQueens problem solution finder using the ThreadPool class. Using n=8 finds the correct count of 92 solutions too fast on my machine to measure the effects of the threading. Bumping the queen count to 14 stretches this time out enough to show all threads being well used.

====

utfNess will detect if a file is UTF-16 LE, UTF-16 BE, or UTF-8.
readFileAsUTF8 will read an entire 8 bit or 16 bit encoded file into an 8 bit string, transfoming UTF-16 to UTF-8.
The conversion is mechanical. Other libraries provide more robust solutions, but this works well in all my tests and
is compact and fast.

====

### Documentation
Everything has either a demo or a test.

The unit tests, use the excellent Catch2 framework.

### Building
You'll need a C++17 compiler.  Tested on recent versions of g++ and clang++

Both CMake and Meson Build files are provided.

CMake is getting to be a defacto standard, but I prefer Meson. Meson's one dependency is Python3 and you can install it using pip.

### License
You can use this library under the terms of the MIT license.
