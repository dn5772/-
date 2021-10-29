import turtle as t
import random


class Ractangle :
    length = None
    color = []
    x = None
    y = None


    def __init__(self):
        self.length = 100

        for i in range(3) :
            c = random.randint(0, 255)
            self.color.append(c)

        self.x = random.randint(-300, 300)
        self.y = random.randint(-300, 300)

    def draw(self):

        t.colormode(255)
        t.penup()
        t.goto(self.x, self.y)
        t.pendown()
        t.pencolor(self.color[0], self.color[1], self.color[2])

        for i in range(4):
            t.forward(self.length)
            t.left(90)

    def changeRact(self):
        for i in range(3) :
            c = random.randint(0, 255)
            self.color[i] = c

        self.x = random.randint(-300, 300)
        self.y = random.randint(-300, 300)

    def loop(self, a):
        for i in range(a):
            self.changeRact()
            self.draw()

class Triangle :
    length = None
    color = []
    x = None
    y = None

    def __init__(self):
        self.length = 60

        for i in range(3) :
            c = random.randint(0, 255)
            self.color.append(c)

        self.x = random.randint(0, 100)
        self.y = random.randint(0, 100)


    def draw(self):
        t.colormode(255)
        t.penup()
        t.goto(self.x, self.y)
        t.pendown()
        t.pencolor(self.color[0], self.color[1], self.color[2])

        for i in range(3):
            t.forward(self.length)
            t.left(120)

    def changeRact(self):
        for i in range(3) :
            c = random.randint(0, 255)
            self.color[i] = c

        self.x = random.randint(-200, 200)
        self.y = random.randint(-200, 200)

    def loop(self, a):
        for i in range(a):
            self.changeRact()
            self.draw()

ract = None
tri = None
ract = Ractangle()
tri = Triangle()

tri.loop(10)
ract.loop(10)
