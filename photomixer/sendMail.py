import os
import sys
import smtplib
from email.mime.text import MIMEText
from email.mime.image import MIMEImage
from email.mime.multipart import MIMEMultipart

PHOTOMIXERuserName = 'm2k21ivs@gmail.com'
PHOTOMIXERpassword = 'maabada123'

def SendPictureInMail(ImgFileName, toMail):

    with open(ImgFileName, 'rb') as f:
        img_data = f.read()

    msg = MIMEMultipart()
    msg['Subject'] = 'Your picture - PHOTOMIXER'
    msg['From'] = PHOTOMIXERuserName
    msg['To'] = str(toMail)

    text = MIMEText("Here is your edited image. Hope you'll enjoy it! PHOTOMIXER :)")
    msg.attach(text)
    image = MIMEImage(img_data, name=os.path.basename(ImgFileName))
    msg.attach(image)

    s = smtplib.SMTP(host='smtp.gmail.com', port=587)
    s.ehlo()
    s.starttls()
    s.ehlo()
    s.login(PHOTOMIXERuserName, PHOTOMIXERpassword)
    s.sendmail(PHOTOMIXERuserName, str(toMail), msg.as_string())
    s.quit()

	
def SendPorgetPasswordMail(toMail, password):

    msg = MIMEMultipart()
    msg['Subject'] = 'Your password - PHOTOMIXER'
    msg['From'] = PHOTOMIXERuserName
    msg['To'] = str(toMail)

    text = MIMEText("Hey friend! This is a mail from photomixer:) . Here is your password: " + password)
    msg.attach(text)

    s = smtplib.SMTP(host='smtp.gmail.com', port=587)
    s.ehlo()
    s.starttls()
    s.ehlo()
    s.login(PHOTOMIXERuserName, PHOTOMIXERpassword)
    s.sendmail(PHOTOMIXERuserName, str(toMail), msg.as_string())
    s.quit()  


# 1-image, 2-forget password
def main():

    if(int(sys.argv[3]) == 1): # image
        SendPictureInMail(sys.argv[1], sys.argv[2])
    if(int(sys.argv[3]) == 2): # forgot password
        SendPorgetPasswordMail(sys.argv[1], sys.argv[2])
	
if __name__ == "__main__":
    main()

