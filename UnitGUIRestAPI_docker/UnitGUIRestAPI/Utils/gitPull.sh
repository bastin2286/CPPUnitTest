
echo "=================PWD=============="

cd /home/bastin/
#Removing the previous file & folders
echo "=================Removing the previous File=============="
echo jenkins | sudo -S rm -rf UnitGUIRestAPI/
echo "=================Clone Command=============="

echo "Checkout the code and test scripts from repo"

#Initially used it for cloning
sudo git clone https://github.com/nandunarayanan/UnitGUIRestAPI.git

#Changing the perrrrmissions of file & folders
sudo chmod 777 -R /home/bastin/UnitGUIRestAPI/
