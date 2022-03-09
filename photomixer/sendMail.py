import os
import smtplib
from email.mime.text import MIMEText
from email.mime.image import MIMEImage
from email.mime.multipart import MIMEMultipart

def SendMail(ImgFileName):
	
    server = smtplib.SMTP(host='smtp.gmail.com', port=587)
    server.ehlo()
    server.starttls()
    server.ehlo()
    server.login('m2k21ivs@gmail.com', 'maabada123')
    server.sendmail('m2k21ivs@gmail.com', 'shellygoman123@gmail.com', 'hey')
    server.quit()
    print("ok")
	
SendMail("images/b.jpg")
