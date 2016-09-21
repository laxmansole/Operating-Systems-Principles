git config --global credential.helper 'cache --timeout 7200'

if [ "$1" == "" ]; then
	echo "Usage: ./git_all.sh \"message\""
else
	git pull
	git add .
	git commit -m "$1" *
	git push
fi




