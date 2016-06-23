eopkg
-----

Gradual clean-room implementation of Solus 2's package manager.


**History**

Solus adopted the PiSi package manager initially due to it's simplistic
concepts, and a break-away from the traditional package manager. After
yet-another-naming-dispute, another group rose to claim the ~~ring of power~~
name as rightfully theirs. In truth, the name is kinda awful in English.
So, we went with a full fork approach and renamed it to **eopkg**.

Quite simply, that meant *Evolve OS Package*. Because, due to yet-another-naming-dispute,
we used to be Evolve OS too. But anywho..

**Divergence**

Shortly after adopting PiSi and renaming to eopkg, we immediately landed features
to, well, make it more useful. These included automatic runtime binary dependencies,
better debuginfo, support for pkg-config names, enhanced emul32 support, etc.
Thus, they stopped being compatible ~~and the ring fell from all knowledge~~.

**Problem**

    Python is really f*****g slow. Don't use it for system-level components.

This is actually compounded when we introduce complex dependency graphs and
what can only be described as an excessive use of XML through a piss-poor-parser.

**Solution**

    One C To Rule Them All.

Pretty much it, really. Tie all the bits we do like, remove all the crap we
severely dislike (Sorry comar, you suck), write it all in C and voila. Bespoke,
high performance package management for Solus, driven solely by Solus ideals,
with a view towards transactional usage and global Solus philosophy such as
*being stateless*. We'll add support for postinstalls but they'll be used
sparingly, and where possible the PM will pick up the bits it needs to.

License
--------

LGPL-2.1. We're going to expose a library for others to use....
