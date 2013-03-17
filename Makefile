all:
	cd src; make

clean:
	rm -rf animat_exp animat_one_run; cd src; make clean

slides:
	cd slides; make

.PHONY: slides