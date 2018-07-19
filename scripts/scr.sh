!#bin/bash
threshold=$(du -b "/home/pi/TKK_PRESA/scripts/touch.txt" | cut -f 1)
bool=true

while $bool;do

  actualsize=$(du -b "/home/pi/TKK_PRESA/scripts/touch.txt" | cut -f 1)
  echo $actualsize
  if [ $actualsize -gt $threshold ]; then
    bool=false
  fi
done

if ! $bool; then
  pkill -f evtest
  rm -f /home/pi/TKK_PRESA/scripts/touch.txt
  cd TKK_PRESA
  make clean
  make
  ./tkk_presa
fi
