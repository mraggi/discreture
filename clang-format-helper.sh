#!/bin/bash
fd "\.[hc]pp" | xargs clang-format -i
fd "\.[hc]pp" | xargs sed -i 's/ \* /\*/g'
fd "\.[hc]pp" | xargs sed -i 's/ \/ /\//g'
fd "\.[hc]pp" | xargs sed -i 's/ \% /%/g'
