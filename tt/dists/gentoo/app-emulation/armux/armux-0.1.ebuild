# Copyright 1999-2009 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

DESCRIPTION="armux is a simulator for the ARM architecture"
HOMEPAGE="http://armdev.googlecode.com/p/armdev/"
SRC_URI="http://armdev.googlecode.com/files/${P}.tar.bz2"

LICENSE="GPLv3"
SLOT="0"
KEYWORDS="~x86"
IUSE=""

DEPEND="sys-libs/readline"
RDEPEND=""

inherit eutils

src_unpack()
{
    unpack ${A}
    cd ${S}
    econf || die "econf failed"
}

src_compile()
{
    emake || die "Compilation failed"
}

src_install()
{
    dobin armux
    dodoc ChangeLog INSTALL
}

pkg_postinst()
{
    einfo "Probando este ebuild"
}


