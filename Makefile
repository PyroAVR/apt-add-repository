all:
	g++ main.cpp -o apt-add-repository
	chmod +x apt-add-repository
install:
	cp apt-add-repository /usr/bin/apt-add-repository
clean:
	rm apt-add-repository
uninstall:
	rm /usr/bin/apt-add-repository
