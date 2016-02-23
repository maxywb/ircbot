
import derived.hello

class PyChild(derived.hello.Parent):
    def foo(self, n):
        return "PyChild %s" % self.name

class PyChildBase(derived.hello.Parent):
    pass

def test():
    parent = derived.hello.Parent("A")
    child = derived.hello.Child("B")
    py_child = PyChild("C")
    py_child_base = PyChildBase("D")

    parent.value = 12
    child.value = 27
    py_child.value = 42
    py_child_base.value = 99

    print parent.foo(2)
    print child.foo(4)
    print py_child.foo(22)
    print py_child_base.foo(9)


