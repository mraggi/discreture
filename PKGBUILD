# Maintainer: Miguel Raggi <mraggi@gmail.com>

pkgname=discreture
pkgver=1.2.1
pkgrel=1
pkgdesc="A modern C++14 library providing iterable objects such as combinations, permutations, partitions, etc."
arch=('x86_64')
url="http://github.com/mraggi/discreture"
license=('Apache')
depends=('boost')
makedepends=('cmake' 'git' 'gtest')
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
    rm -rf build
    mkdir build && cd build
    cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release ..
    make
}

package() {
    cd "$srcdir/discreture"
	

    install -Dm644 README.md "$pkgdir/usr/share/doc/$_gitname/README.md" || return 1
    cd build
    make DESTDIR="$pkgdir/" install
}

