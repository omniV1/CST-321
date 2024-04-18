#!/bin/bash

# Password Validator Script

password="$1"  # Get the password from the first command line argument

# Check for minimum length of 8 characters
if [[ ${#password} -lt 8 ]]; then
  echo "Password validation failed: Length should be at least 8 characters."
fi

# Check for presence of at least one numeric character
if ! [[ "$password" =~ [0-9] ]]; then
  echo "Password validation failed: Must contain at least one numeric character."
fi

# Check for presence of at least one special character (@, #, $, %, *, +, =)
if ! [[ "$password" =~ [@#$%*+=] ]]; then
  echo "Password validation failed: Must contain at least one special character (@, #, $, %, *, +, =)."
fi

# If all conditions are met
if [[ ${#password} -ge 8 ]] && [[ "$password" =~ [0-9] ]] && [[ "$password" =~ [@#$%*+=] ]]; then
  echo "Password validation passed."
fi
