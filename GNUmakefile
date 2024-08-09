# Onur is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Onur is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Onur. If not, see <https://www.gnu.org/licenses/>.

# DEPS: gcc meson ninja muon coreutils valgrind indent splint cunit

.DEFAULT_GOAL: test
PREFIX     ?= ${HOME}/.local/bin
NAME       = onur-cpp
RM         = rm -rf
BUILDDIR = ./build

RUNNER := podman
VERSION := $(shell awk -F "'" '/version:/ { print $$2; exit }' meson.build)
CONTAINER_IMAGE := registry.gitlab.com/${USER}/${NAME}:${VERSION}

# ------------------------------------ TASKS

.PHONY: all
all: cmake.all

.PHONY: dev
dev: cmake.dev

.PHONY: meson.all
meson.all:
	CC=g++ meson setup $(BUILDDIR) --wipe
	CC=g++ meson compile -C $(BUILDDIR)


.PHONY: meson.dev
meson.dev:
	CC=g++ meson setup $(BUILDDIR)
	CC=g++ meson compile -C $(BUILDDIR)

.PHONY: cmake.all
cmake.all: clean
	cmake -S . -B ${BUILDDIR} -D CMAKE_BUILD_TYPE=Release
	cmake --build ${BUILDDIR}

.PHONY: cmake.dev
cmake.dev:
	cmake -S . -B ${BUILDDIR} -D CMAKE_BUILD_TYPE=Debug
	cmake --build ${BUILDDIR}

.PHONY: clean
clean:
	@$(RM) $(BUILDDIR)

.PHONY: install
install:
	cp -v ${BUILDDIR}/src/onur ${PREFIX}/onur

.PHONY: uninstall
uninstall:
	rm ${PREFIX}/${NAME}

.PHONY: format
format:
	clang-format -i ./src/*.cpp ./include/*.hpp

.PHONY: lint
lint:
	clang-check ./src/*.cpp

.PHONY: leaks
leaks:
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         ./build/onur grab
         # --log-file=valgrind-output \

# ------------------------------- CONTAINER

.PHONY: image.build
image.build:
	${RUNNER} build --file ./Containerfile --tag ${CONTAINER_IMAGE} --env ONUR_VERSION=${VERSION}

.PHONY: image.repl
image.repl:
	${RUNNER} run --rm -it \
		--volume ${PWD}:/app:Z \
		--workdir /home/easbarba/app \
		${CONTAINER_IMAGE} bash

.PHONY: image.publish
image.publish:
	${RUNNER} push ${CONTAINER_IMAGE}

.PHONY: test
test:
	${RUNNER} run --rm -it \
		--volume ${PWD}:/app:Z \
		--workdir /home/easbarba/app \
		${CONTAINER_IMAGE} bash -c "meson test -C build"

.PHONY: image.commands
image.commands:
	${RUNNER} run --rm -it \
		--volume ${PWD}:/app:Z \
		--workdir /home/easbarba/app \
		${CONTAINER_IMAGE} bash -c "$(shell cat ./container-commands | fzf)"
