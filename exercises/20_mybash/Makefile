REPO_ROOT := $(abspath .)

.PHONY: all clean $(SUBDIRS) mybash

SUBDIRS := mysed myfile mywc mytrans

all: mybash

mysed myfile mywc mytrans:
	$(MAKE) -C src/$@ REPO_ROOT=$(REPO_ROOT)

mybash: $(SUBDIRS)
	$(MAKE) -C src/mybash REPO_ROOT=$(REPO_ROOT)

clean:
	rm -rf $(REPO_ROOT)/bin $(REPO_ROOT)/obj
	@for d in mysed myfile mywc mytrans mybash; do \
		$(MAKE) -C src/$$d clean REPO_ROOT=$(REPO_ROOT) 2>/dev/null || true; \
	done
