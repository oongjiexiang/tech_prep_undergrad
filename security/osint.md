# Find Other's User ID
1. For Google accounts, add the person's gmail on Google Chat
2. Find `data-member-id` attribute in Inspector tab. To verify, check that the tag that contains this attribute also has `data-name` set to his gmail
3. Access his Google service info
   - `https://get.google.com/albumarchive/{userID}`
   - `https://www.google.com/maps/contrib/{userID}`

# Phishing
If domain X is often spoofed for phishing, it may be due to two reasons:
1. Email authentication is weak: **SPF Record Lookup** may reveal that every possible email may claim to be from X
2. Weak policy stated in DMARC: even though the email fails DMARC test, nothing is done

Tool: MxToolbox