import os
import sys
import smtplib
from email.mime.text import MIMEText
from email.mime.image import MIMEImage
from email.mime.multipart import MIMEMultipart

PHOTOMIXERuserName = 'itsphotomixer@gmail.com'
PHOTOMIXERpassword = 'ineshelly17'

def SendPictureInMail(filename, mail):

    with open(filename, 'rb') as f:
        img_data = f.read()

    msg = MIMEMultipart()
    msg['Subject'] = 'Your picture - PHOTOMIXER'
    msg['From'] = PHOTOMIXERuserName
    msg['To'] = str(mail)

    text = MIMEText("Here is your edited image. Hope you'll enjoy it! PHOTOMIXER :)")
    msg.attach(text)
    image = MIMEImage(img_data, name=os.path.basename(filename))
    msg.attach(image)

    s = smtplib.SMTP(host='smtp.gmail.com', port=587)
    s.ehlo()
    s.starttls()
    s.ehlo()
    s.login(PHOTOMIXERuserName, PHOTOMIXERpassword)
    s.sendmail(PHOTOMIXERuserName, str(toMail), msg.as_string())
    s.quit()
	
    
def SendPorgetPasswordMail(mail, password):

    msg = MIMEMultipart()
    msg['Subject'] = 'Your password - PHOTOMIXER'
    msg['From'] = PHOTOMIXERuserName
    msg['To'] = str(mail)

    text = MIMEText("Hey friend! This is a mail from photomixer:) . Here is your password: " + password)
    msg.attach(text)

    s = smtplib.SMTP(host='smtp.gmail.com', port=587)
    s.ehlo()
    s.starttls()
    s.ehlo()
    s.login(PHOTOMIXERuserName, PHOTOMIXERpassword)
    s.sendmail(PHOTOMIXERuserName, str(mail), msg.as_string())
    s.quit()  


# parameters: 
# filename mail flag
# mail password flag
def main():
    if(int(sys.argv[3]) == 1): # image
        SendPictureInMail(sys.argv[1], sys.argv[2])
    if(int(sys.argv[3]) == 2): # forgot password
        SendPorgetPasswordMail(sys.argv[1], sys.argv[2])
	
if __name__ == "__main__":
    main()

