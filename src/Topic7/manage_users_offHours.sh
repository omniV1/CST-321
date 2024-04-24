#!/bin/bash

# Define office hour start and end times (24-hour format)
office_start=0800
office_end=1700

# Print header
echo "Logins outside office hours:"

# Filter auth.log by time, outside of office hours
awk -v start="$office_start" -v end="$office_end" '{
  # Extract the month, day, and time
  month = $1;
  day = $2;
  time = $3;

  # Convert time to 24-hour format without colon
  gsub(":", "", time);

  # Check if the time is outside of office hours and print the line if it is
  if ((time < start && time >= "0000") || (time > end && time <= "2359") && $0 !~ /CRON/) {
    print month, day, time, $0;
  }
}' /var/log/auth.log | grep "session opened"
