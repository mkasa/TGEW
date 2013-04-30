==============================
TGEW: Tiny Grid Engine Wrapper
==============================

What is TGEW?
=============

If you do not use Sun Grid Engine (or an equivalent like N1GE, Univa Grid Engine), this software is not useful for you.
TGEW is a system that allows you to submit jobs easily, especially if your jobs have dependencies.
tge_make is a utility that is almost compatible to GNU make, but can utilize paralallisms in a grid environment.
TGEW also includes several utility tools that will make it easier to manage jobs.

Prerequisites
=============

TGEW requires following libraries

- GNU Make
- Perl module 'Term::ReadKey' for qtop

If you do not use qtop, you do not need to install Term::ReadKey.
TGEW assumes that working directories are shared among nodes; if storage is not shared among nodes, or the path to the shared storage is not identical across nodes, TGEW would not work.

Build & Install
===============

TGEW uses waf for its packaging system. To configure, do as follows::

        $ ./configure

Then, do make and make install,::

        $ make && make install

Before using programs in TGEW, do 'tge_install' once, and answer some questions.::

        $ tge_install

How to Use tge_make
===================

A program that inputs file(s) and outputs file(s) is called a job, hereafter.
We often have a computational pipeline in which multiple jobs are executed and some of them have dependencies; some job might be executed only after some job is completed.
You can write such a pipeline in the form of Makefile, which can be executed by 'make -j' if all CPU cores you want to use is on a single machine.
tge_make brings it into a grid environment in which CPU cores are distributed across multiple nodes.

Write Makefile as usual. Debug it with 'make -j' on a single machine. If it worked as you expected, do 'tge_make -bg' with a grid environment.
tge_make executes GNU make to create the dependency graph of the input jobs, and creates shell scripts that create each target file, which are then qsub'ed to a grid with appropriate dependencies.

What is nice with TGEW
======================

I know that qmake can do similar tasks. However, tge_make does better than qmake.
qmake does not work well especially when the queue is not ready for some time. tge_make works more stably under busy loads.

qmake submits a job every time a job is ready to go; a job will not be submitted until all dependent jobs are done.
Suppose that the queue is very busy and hundreads of jobs are waiting for being run. You are using qmake, and you have hundred jobs, J1, J2, ..., J100.
Suppose that J{n+1} should be run only after J{n} is completed. First, you see that J1 is run. Soon after J1 is completed, J2 is submitted.
Since there are already hundreds of jobs in the queue, J2 sits after them, having to wait for quite a long time.
Let's say J2 is run after waiting 10 hours. J2 is completed, and J3 is sent to the queue. You will see that J3 is at the last of the queue.
You are so irriated that you throw qmake away, and decided to use tge_make instead.

tge_make submits all jobs (with proper dependencies) first, so that you will not be bothered in such a situation.
It also takes care of several environmental variables, the shell settings and so on. I believe you get less frustrated with tge_make than with qmake.

Utility scripts
===============

qtop is a top-like command that shows the status of hosts.
tge_del is a job deleting tool like qdel. tge_del can accepts a regexp to specify a bunch of jobs whose job name matches to the regexp.

License
=======

This software is distributed under modified BSD license
(http://www.opensource.org/licenses/bsd-license.php)

