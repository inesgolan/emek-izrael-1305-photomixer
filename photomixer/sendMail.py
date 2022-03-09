import os
import smtplib
from email.mime.text import MIMEText
from email.mime.image import MIMEImage
from email.mime.multipart import MIMEMultipart

def SendMail(ImgFileName):

    with open(ImgFileName, 'rb') as f:
        img_data = f.read()

    msg = MIMEMultipart()
    msg['Subject'] = 'Hey'
    msg['From'] = 'm2k21ivs@gmail.com'
    msg['To'] = 'shellygoman123@gmail.com'

    text = MIMEText("test")
    msg.attach(text)
    image = MIMEImage(img_data, name=os.path.basename(ImgFileName))
    msg.attach(image)

    s = smtplib.SMTP(host='smtp.gmail.com', port=587)
    s.ehlo()
    s.starttls()
    s.ehlo()
    s.login('m2k21ivs@gmail.com', 'maabada123')
    s.sendmail('m2k21ivs@gmail.com', 'shellygoman123@gmail.com', msg.as_string())
    s.quit()






	
    # server = smtplib.SMTP(host='smtp.gmail.com', port=587)
    # server.ehlo()
    # server.starttls()
    # server.ehlo()
    # server.login('m2k21ivs@gmail.com', 'maabada123')
    # server.sendmail('m2k21ivs@gmail.com', 'shellygoman123@gmail.com', 'hey')
    # server.quit()
    print("ok")
	
SendMail("images/b.jpg")
