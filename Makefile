#change this to g++ by making with 
# CC=g++ make all

CC=clang++

all:
	$(CC) main.cpp -o apt-add-repository
	chmod +x apt-add-repository
install:
	cp apt-add-repository /usr/bin/apt-add-repository
	update-alternatives --install /usr/bin/add-apt-repository add-apt-repository /usr/bin/apt-add-repository 50
clean:
	rm apt-add-repository
uninstall:
	rm /usr/bin/apt-add-repository
