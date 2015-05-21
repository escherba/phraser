.PHONY: clean coverage develop env extras package release test virtualenv

CC = clang++

SRC_ROOT = phraser/
BIN_DIR = bin/


FLAGS_BASE = \
    -std=c++11 \
    -fcolor-diagnostics \
    -O3 \
    -ferror-limit=5 \
    -I$(SRC_ROOT) \
    -lboost_regex \

FLAGS_WARN = \
    -Wpedantic \
    -Wall \
    -Weverything \
    -Wextra \
    -Werror \

FLAGS_WARN_DISABLE = \
    -Wno-c++98-compat-pedantic \
    -Wno-covered-switch-default \
    -Wno-exit-time-destructors \
    -Wno-global-constructors \
    -Wno-padded \
    -Wno-weak-vtables \

FLAGS_WARN_DISABLE_LAPOS = \
    -Wno-shorten-64-to-32 \
    -Wno-sign-conversion \
    -Wno-old-style-cast \
    -Wno-sign-compare \
    -Wno-float-equal \
    -Wno-unused-variable \
    -Wno-unused-parameter \
    -Wno-unused-function \

FLAGS = $(FLAGS_BASE) $(FLAGS_WARN) $(FLAGS_WARN_DISABLE) \
        $(FLAGS_WARN_DISABLE_LAPOS)

PYENV = . env/bin/activate;
PYTHON = $(PYENV) python
EXTRAS_REQS := $(wildcard requirements-*.txt)
DISTRIBUTE = sdist bdist_wheel

package: env
	$(PYTHON) setup.py $(DISTRIBUTE)

release: env
	$(PYTHON) setup.py $(DISTRIBUTE) upload -r livefyre

# if in local dev on Mac, `make coverage` will run tests and open
# coverage report in the browser
ifeq ($(shell uname -s), Darwin)
coverage: test
	open cover/index.html
endif

test: extras
	$(PYENV) nosetests $(NOSEARGS)
	$(PYENV) py.test README.rst

extras: env/make.extras
env/make.extras: $(EXTRAS_REQS) | env
	rm -rf env/build
	$(PYENV) for req in $?; do pip install -r $$req; done
	touch $@

nuke: clean
	rm -rf *.egg *.egg-info env bin cover coverage.xml nosetests.xml

clean:
	python setup.py clean
	rm -rf dist build $(BIN_DIR)
	find . -path ./env -prune -o -type f -name "*.pyc" -exec rm {} \;
	find . -path ./env -prune -o -type f -name "*.so" -exec rm {} \;

compare_against_impermium:
	mkdir -p $(BIN_DIR)
	$(CC) `find -type f -name "*.cc"` $(SRC_ROOT)/tools/compare_against_impermium.cpp -o $(BIN_DIR)/compare_against_impermium $(FLAGS)

memcheck:
	time valgrind --leak-check=full --track-origins=yes ./bin/compare_against_impermium /media/x/impermium_dedup/50k_comments.txt > valgrind_stdout.txt 2> valgrind_stderr.txt

develop:
	@echo "Installing for " `which pip`
	pip uninstall $(PYMODULE) || true
	python setup.py develop

env virtualenv: env/bin/activate
env/bin/activate: requirements.txt setup.py
	test -f $@ || virtualenv --no-site-packages env
	$(PYENV) pip install -U pip wheel
	$(PYENV) pip install -e . -r $<
	$(PYTHON) setup.py build_ext --inplace
	touch $@
