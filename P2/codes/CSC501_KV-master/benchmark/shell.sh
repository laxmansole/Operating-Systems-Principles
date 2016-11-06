## in the benchamark directory,
1. make clean; make all
2. ./getsettest > op
3. cp op op1 # taking a back-up
4. vim op; #opening op file to do some sorts
## inside the file , do :%!sort -n -k3,3 -k2,6; this will sort based on col-3 (keyvalue and then col-2 the tids); then delete all lines with G( search for G by /G; then do :g//d to delete all lines having G ) and delete all of the size wala column (col4)--hindering with sorting later. can do this by visual select- ctrl-V and deleting only selected column. 
#then save op and quit by :wq

5. for i in `seq 0 65535`; do grep "\s$i\s" op| tail -1; done > 2
6. cat 2 | ./validate 65536
