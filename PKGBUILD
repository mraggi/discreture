# Maintainer: oi_wtf <brainpower at mailbox dot org>

pkgname=discreture
pkgver=1.0
# pkgrel=0
pkgdesc="A modern C++14 library providing iterable objects such as combinations, permutations, partitions, etc."
arch=('x86_64')
url="http://github.com/mraggi/discreture"
license=('Apache')
# depends=('gcc')
makedepends=('cmake' 'doxygen' 'git')
provides=('discreture')
conflicts=('discreture')
replaces=('discreture')
# options=('debug')

source=("git+https://github.com/mraggi/discreture.git")
sha256sums=('SKIP')

# prepare() {
#     git clone https://github.com/mraggi/discreture.git
#     
# }

build() {
    cd "$srcdir/discreture"
    cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release .
    make
}

package() {
    cd "$srcdir/discreture"

    make DESTDIR="$pkgdir/" install

#     install -Dm644 ./license.txt ${pkgdir}/usr/share/licenses/${pkgname}/LICENSE
    install -Dm644 README.md "$pkgdir/usr/share/doc/$_gitname/README.md" || return 1
#     install 
}
