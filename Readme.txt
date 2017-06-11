TITLE : Text editor using GTK
PriteshKumar Jugalkishor Holani
	
	* My text editor need gtk library to be installed on system.
	* Install gtk by copying command in terminal
		sudo apt-get install gnome-core-devel build-essential 
	* Text editor uses the in built function of gtk library to perform 
	   all operations such as save , open, cut, copy , paste, find and provide 
	   good interface between user and editor
	* To save file first it loads all the contents of file (buffer) on textview widget and 
	   then check file is modified or not if modified then it show user to save modified 
	   file.
	* To open file from file manager , provide file location to open the file.
	* To cut, copy, paste use keyboard shortcuts and it is done by using gtk clipboard.
	* To find text from given file it takes start and end values of buffer and then searches 
	   for it, and if found mark it. For next search the same procedure is applied.
	* In help all neccesary instructions are provided to use the text editor.        


