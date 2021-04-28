minicom:
	sshpass -p 'xinurocks' ssh -o StrictHostKeyChecking=no -t xinu@127.0.0.1 -p 2222 "sudo minicom" 

run: transfer_zip
	sshpass -p "xinurocks" ssh xinu@localhost -p 2222 "rm -rf xinu && tar -xf xinu.tar && cd ~/xinu/compile && make clean && make && exit"

transfer_zip: zip
	sshpass -p "xinurocks" scp -P 2222 ~/FINAL-XINU-OS/xinu.tar xinu@localhost:~/

zip:
	tar -cf xinu.tar xinu

backend_start: 
	VBoxManage startvm "backend" 

backend_stop:
	VBoxManage controlvm "backend" poweroff

dev_start:
	VBoxManage startvm "development-system" --type headless 

dev_stop:
	VBoxManage controlvm "development-system" poweroff  --type headless 
