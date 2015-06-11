#!/bin/bash
grep -v '^end$' | \
grep -v '^and$' | \
awk -F':' 'BEGIN{title=0} {if($1=="title"){title+=1;if(title > 1){exit 0}};print $0}'
