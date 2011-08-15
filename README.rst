==============================
TGEW: Tiny Grid Engine Wrapper
==============================

What is TGEW?
=============

If you do not use Sun Grid Engine, this software is not useful for you.
TGEW is a system that allows you to submit jobs easily, especially if
your jobs have dependencies.

Prerequisites
=============

TGEW requires following libraries::

* Perl module 'Term::ReadKey' for qtop


Build & Install
===============

TGEW uses waf for its packaging system. To configure, do as follows::

        $ ./configure

Then, do make and make install,::

        $ make && make install


License
=======

This software is distributed under modified BSD license
(http://www.opensource.org/licenses/bsd-license.php)

