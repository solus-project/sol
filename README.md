sol
----

Replacement for `eopkg`, the Solus package manager (a fork of eopkg).

This is not an effort to create "yet another package manager", it is instead
a current research effort for the successor to `eopkg`, to create a modern
package manager to deal with the needs of today, and of Solus itself.

 - Spend less time downloading
 - Spend less time applying updates
 - Don't ever break. (ABI, layout, config, etc.)

The Solus mantra is "Install today, update forever". We need a modern software
and update management system to handle this in the most efficient manner for
the user, to truly handle the needs of a modern rolling release designed for
the ordinary user.

More details will be fleshed out as and when we've settled on them. In the
mean time, don't panic. :]

`sol` is a [Solus project](https://solus-project.com/)

![logo](https://build.solus-project.com/logo.png)

Initial TODO
------------

Every project needs a TODO list.. let's not get too ambitious yet.

 - [x] Rename to something undumb (sol)
 - [ ] Kill autotools with a shovel
 - [ ] Move most of the existing eopkg code into a `Migration` system.
 - [ ] Add basic container format
 - [ ] Implement basic install/remove ops
 - [ ] Add first abstract DB implementation
 - [ ] Start adding networking
 - [ ] Introduce repo format + handling
 - [ ] Add stuff to this TODO.


License
--------

Copyright © 2016-2017 Ikey Doherty

LGPL-2.1. We're going to expose a library for others to use....
