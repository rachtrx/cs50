# # option 1
# class Circle:
#     def __init__(self, radius):
#         self._radius = radius

#     def _get_radius(self):
#         print("Get radius")
#         return self._radius

#     def _set_radius(self, value):
#         print("Set radius")
#         self._radius = value

#     def _del_radius(self):
#         print("Delete radius")
#         del self._radius

#     radius = property(
#         fget=_get_radius,
#         fset=_set_radius,
#         fdel=_del_radius,
#         doc="The radius property."
#     )

# option 2
class Circle:
    def __init__(self, radius):
        self._radius = radius

    @property
    def radius(self):
        """The radius property."""
        print("Get radius")
        return self._radius

    @radius.setter
    def radius(self, value):
        print("Set radius")
        self._radius = value

    @radius.deleter
    def radius(self):
        print("Delete radius")
        del self._radius


# >>> from circle import Circle

# >>> circle = Circle(42.0)

# >>> circle.radius
# Get radius
# 42.0

# >>> circle.radius = 100.0
# Set radius
# >>> circle.radius
# Get radius
# 100.0

# >>> del circle.radius
# Delete radius
# >>> circle.radius
# Get radius
# Traceback (most recent call last):
#     ...
# AttributeError: 'Circle' object has no attribute '_radius'

# >>> help(circle)
# Help on Circle in module __main__ object:

# class Circle(builtins.object)
#     ...
#  |  radius
#  |      The radius property.