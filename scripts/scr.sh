!#bin/bash
threshold=$(du -b "/home/pi/TKK_TRESENJE/scripts/touch.txt" | cut -f 1)
bool=true

while $bool;do

  actualsize=$(du -b "/home/pi/TKK_TRESENJE/scripts/touch.txt" | cut -f 1)
  echo $actualsize
  if [ $actualsize -gt $threshold ]; then
    bool=false
  fi
done

if ! $bool; then
  pkill -f evtest
  rm -f /home/pi/TKK_TRESENJE/scripts/touch.txt
  cd PRESA
  make clean
  make
  #valgrind --tool=callgrind ./presa
  ./presa 
  #rm /home/pi/touch.txt
fi
