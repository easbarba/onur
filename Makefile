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

PREFIX     ?= ${HOME}/.local/bin
NAME       = onur
RM         = rm -rf

BUILDDIR = ./build

# ------------------------------------ TASKS

.PHONY: all
all: deps
	meson compile -C $(BUILDDIR)

.PHONY: deps
deps:
	CC=gcc meson setup build --wipe

.PHONY: dev
dev:
	meson compile -C $(BUILDDIR)

# .PHONY: all
# all:
# 	cmake -B ${BUILDDIR} -S .
# 	cmake --build ${BUILDDIR}

# .PHONY: dev
# dev:

.PHONY: test
test:
	@echo "testing"

.PHONY: clean
clean:
	@$(RM) $(BUILDDIR)

.PHONY: install
install:
	cp -v ${BUILDDIR}/${NAME} ${PREFIX}/${NAME}

.PHONY: uninstall
uninstall:
	rm ${PREFIX}/${NAME}

.PHONY: format
format:
	indent -l 80 -gnu -nut -bl  src/*.c

.PHONY: lint
lint:
	splint -preproc -unrecog -warnposix src/*.c

.PHONY: leaks
leaks:
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         ./build/onur grab
         # --log-file=valgrind-output \

# ------------------------------------ ACTIONS

.PHONY: default
default:
	$(BUILDDIR)/$(NAME)

.PHONY: usage
usage:
	$(BUILDDIR)/$(NAME) --help

.PHONY: grab
grab:
	$(BUILDDIR)/$(NAME) grab

.PHONY: backup
backup:
	$(BUILDDIR)/$(NAME) backup meh,foo,bar


.DEFAULT_GOAL: test
