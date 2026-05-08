<?xml version="1.0" encoding="UTF-8"?>
<!-- Lab 8.2: Display XML in tabular format. -->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="html" indent="yes" />
    <xsl:template match="/root">
        <html>
            <body>
                <h2>Details</h2>
                <table border="1">
                    <tr bgcolor="fuchsia">
                        <th>Name</th>
                        <th>Price</th>
                        <th>Address</th>
                    </tr>
                    <xsl:for-each select="detail">
                        <tr>
                            <td><xsl:value-of select="name" /></td>
                            <td><xsl:value-of select="price" /></td>
                            <td><xsl:value-of select="address" /></td>
                        </tr>
                    </xsl:for-each>
                </table>
            </body>
        </html>
    </xsl:template>
</xsl:stylesheet>