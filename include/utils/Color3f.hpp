////////////////////////////////////////////////////////////////////////////////
// Guacamole - An interesting scenegraph implementation.
//
// Copyright: (c) 2011-2012 by Felix Lauer and Simon Schneegans
// Contact:   felix.lauer@uni-weimar.de / simon.schneegans@uni-weimar.de
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
//
/// \file
/// \brief Declaration of the Color3f struct.
////////////////////////////////////////////////////////////////////////////////

# ifndef COLOR_3F_HPP
# define COLOR_3F_HPP

/// A struct for color handling.
/// It stores the color in RGB values, but provides an HSV
/// interface as well.

namespace gua {

struct Color3f {
    public:
        /// Default ctor, black.
        Color3f ();
        /// Copy ctor.
        Color3f (Color3f const& color);
        /// Ctor from RGB values.
        Color3f (float red, float green, float blue);

        /// \name Getters
        ///@{

        /// Returns the red part of the color.
        float r() const;
        /// Returns the green part of the color.
        float g() const;
        /// Returns the blue part of the color.
        float b() const;
        /// Returns the hue of the color.
        float h() const;
        /// Returns the saturation of the color.
        float s() const;
        /// Returns the value of the color.
        float v() const;
        ///@}

        /// \name Setters
        ///@{

        /// Sets the red part of the color.
        void r(float red);
        /// Sets the green part of the color.
        void g(float green);
        /// Sets the blue part of the color.
        void b(float blue);
        /// Sets the hue of the color.
        void h(float hue);
        /// Sets the saturation of the color.
        void s(float saturation);
        /// Sets the value of the color.
        void v(float value);
        ///@}

        /// Inverts the color.
        Color3f const inverted() const;

        /// Brightens the color if it is too dark
        Color3f const brightened() const;

        /// Creates a random color struct.
        static const Color3f random();

    private:
        /// Helper function to set the RGB values from HSV values.
        void set_hsv (float hue, float saturation, float value);

        /// \name Data
        /// The members storing the color information in RGB values.
        /// They are clamped from 0.0 to 1.0
        ///@{
        float r_, g_ , b_;
        ///@}
};

/// Multiplication of a color with a float.
Color3f      operator*  (float const& lhs, Color3f rhs);
Color3f      operator*  (Color3f const& lhs, float rhs);

/// Addition of two colors. Clamped.
Color3f      operator+  (Color3f const& lhs, Color3f const& rhs);

/// Subtraction of two colors. Clamped.
Color3f      operator-  (Color3f const& lhs, Color3f const& rhs);

/// Division of a color by a float.
Color3f      operator/  (Color3f const& lhs, float rhs);

}

# endif //COLOR_3F_HPP
