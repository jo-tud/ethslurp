#abi_lib=libethabi.a
curl_lib=/usr/lib/libcurl.dylib
#curl_lib=/usr/lib/x86_64-linux-gnu/libcurl.so.4
cflags=-std=c++11 -Wall -O2 -DLINUX -I. -I./utillib -I./etherlib -I./daolib
libs=$(curl_lib) $(abi_lib) */*.a

product=ethslurp
src= \
ethslurp.cpp \
slurp_options.cpp

#-------------------------------------------------
# probably don't have to change below this line

objects = $(patsubst %.cpp,objs/%.o,$(src))
objs=./objs

all:
	@cd utillib; make; cd ..
	@cd etherlib; make; cd ..
	@cd daolib; make; cd ..
	@echo "$(product) build started"
	@echo "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"
	@make $(product)
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"

data: test

test: all
	@cd theData/tests; make; cd -
	@cd theData/theDAO; make; cd -
	@cd theData/funcs; make; cd -
	@cd theData/ghc; make; cd -
	@cd theData/otherContracts; make; cd -
	@cd theData/whales; make; cd -
	@cd theData/hack; make; cd -
	@make -B back

#	@cd src/summation ; make data ; cd -

back:
	@rm -fR theData/backup
	@cp -pR ~/.ethslurp theData/backup
#	@rm -fR theData/backup/slurps

$(product): $(objects) $(libs)
	$(CXX) -o $(product) $(objects) $(libs)
	@strip $(product)

$(objects): | objs

objs:
	@mkdir -p $@

objs/%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(cflags) -c $< -o $@

cleanall:
	@make clean

clean:
	@cd utillib; make clean; cd ..
	@cd etherlib; make clean; cd ..
	@cd daolib; make clean; cd ..
	-@$(RM) -f $(product) $(objs)/*.o $(objs)/*.a 2> /dev/null
