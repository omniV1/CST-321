#!/bin/bash
# This script checks for logins outside of office hours from 8:00AM to 5:00PM

echo "Logins outside office hours:"
awk -F: '{ if ($3 < 800 || $3 > 1700) print $0 }' /var/log/auth.log | grep -i "session opened"
