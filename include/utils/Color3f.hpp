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

namespace gua {

////////////////////////////////////////////////////////////////////////
/// \brief A struct for color handling.
///
/// This class stores color values in RGB manner, but provides an HSV
/// interface as well.
////////////////////////////////////////////////////////////////////////

struct Color3f {
    public:

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// This constructs a Color with all values set to 0 (black).
        ////////////////////////////////////////////////////////////////////////
        Color3f ();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Copy constructor.
        ///
        /// This constructs a Color from an existing one.
        ///
        /// \param color    The existing color to be copied.
        ////////////////////////////////////////////////////////////////////////
        Color3f (Color3f const& color);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// This constructs a Color from given RGB values.
        ///
        /// \param red       The red value.
        /// \param green     The green value.
        /// \param blue      The blue value.
        ////////////////////////////////////////////////////////////////////////
        Color3f (float red, float green, float blue);

        ///@{
        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns a single Color value.
        ////////////////////////////////////////////////////////////////////////
        float r() const;
        float g() const;
        float b() const;
        float h() const;
        float s() const;
        float v() const;
        ///@}

        ///@{
        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets a single Color value.
        ///
        /// \param value    The new value to be set.
        ////////////////////////////////////////////////////////////////////////
        void r(float red);
        void g(float green);
        void b(float blue);
        void h(float hue);
        void s(float saturation);
        void v(float value);
        ///@}

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns an inverted copy of the Color.
        ///
        /// \param color      The inverted copy of the Color.
        ////////////////////////////////////////////////////////////////////////
        Color3f const inverted() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns an inverted copy of the Color.
        ///
        /// \param color      The inverted copy of the Color.
        ////////////////////////////////////////////////////////////////////////
        Color3f const brightened() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns a randomly generated Color.
        ///
        /// \return color      A randomly generated color.
        ////////////////////////////////////////////////////////////////////////
        static const Color3f random();

    private:
        void set_hsv (float hue, float saturation, float value);

        float r_, g_ , b_;
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
