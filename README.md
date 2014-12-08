apt-add-repository
==================

**Translates Ubuntu "PPAs" into standard Deb package configurations -- without the Ubuntu.**
A very simple program which does exactly that.  apt-add-repository takes "ppa:something/program" and turns it into "deb http://ppa.launchpad.net/something/program/ubuntu trusty main" or similar.

# How to use
**apt-add-repository ppa:something/program [OPTIONS]**
Command line options:

-h | --help | help Print a help text.

-r Change the Ubuntu release to use. ie: hardy, trusty, precise, etc. (Hardy Heron 8.04 FTW!)

# Why
The name actually follows the A-P-T naming scheme of apt-some-derivative-command, ie: apt-get, apt-cache, apt-file.
This is less confusing (to me and other people with OCD, anyways...) and also differentiates it from add-apt-repository, the official Ubuntu program that does this.
apt-add repository also works on other systems, which was the main goal. Ideally, it should work on any distro which uses the Advanced Package Tool, which, if you aren't a guru, is usually a Debian derivative. (Ubuntu, Mint, Crunchbang #!, Titanium, etc.) [shameless prop to my new distro!]
Please enjoy!  Report bugs here!  I'll gladly fix them!
