if [ "$1" == "" ]; then
	echo "Usage: ./git_all.sh \"message\""
else
	git add .
	git commit -m "$1" *
	git push
fi




