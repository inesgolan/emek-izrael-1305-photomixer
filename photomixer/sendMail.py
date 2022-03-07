import os
import smtplib
from email.mime.text import MIMEText
from email.mime.image import MIMEImage
from email.mime.multipart import MIMEMultipart

def SendMail(ImgFileName):
    with open(ImgFileName, 'rb') as f:
        img_data = f.read()

    msg = MIMEMultipart()
    msg['Subject'] = 'my picturee'
    msg['From'] = 'shellygoman123@gmail.com'
    msg['To'] = 'noagolan1212@עmail.com'

    text = MIMEText("test")
    msg.attach(text)
    image = MIMEImage(img_data, name=os.path.basename(ImgFileName))
    msg.attach(image)
    
    try:
        s = smtplib.SMTP('localhost') # check
        s.ehlo()
        s.starttls()
        s.ehlo()
        s.login("shellygoman123@gmail", " password") # 
        s.sendmail(From, To, msg.as_string())
        s.quit()
    except SMTPException:
       print "Error: unable to send email"
	
	
SendMail("images/b.jpg")