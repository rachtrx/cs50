# https://preview.redd.it/02mbtg5rnq691.png?width=934&format=png&auto=webp&v=enabled&s=d214c528186502e9ef459674a7a16a15a033bca1

class Jar:
    def __init__(self, capacity=12):
        self.capacity = capacity
        if self.capacity < 0:
            raise ValueError("less than 0!")
        self.size = 0

    def __str__(self):
        return (self.size * '🍪')

    def deposit(self, n):
        self.size += n
        if self.size > self.capacity:
            raise ValueError("Full!")
        else:
            return self.size

    def withdraw(self, n):
        self.size -= n
        if self.size < 0:
            raise ValueError("Empty!")
        else:
            return self.size

    @property
    def capacity(self):
        return self._capacity

    @capacity.setter
    def capacity(self, value):
        self._capacity = value

    @property
    def size(self):
        return self._size

    @size.setter
    def size(self, value):
        self._size = value

def main():
    jar = Jar(12)
    print(str(jar.capacity))
    jar.deposit(13)
    print(str(jar))
    jar.withdraw(1)
    print(str(jar))

if __name__ == "__main__":
    main()