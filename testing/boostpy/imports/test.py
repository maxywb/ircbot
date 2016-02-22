
import derived.hello

class PyChild(derived.hello.Parent):
    def foo(self):
        return "PyChild %s" % self.name

class PyChildBase(derived.hello.Parent):
    pass

parent = derived.hello.Parent("A")
child = derived.hello.Child("B")
py_child = PyChild("C")
py_child_base = PyChildBase("D")

parent.value = 12
child.value = 27
py_child.value = 42
py_child_base.value = 99

print parent.foo()
print child.foo()
print py_child.foo()
print py_child_base.foo()


