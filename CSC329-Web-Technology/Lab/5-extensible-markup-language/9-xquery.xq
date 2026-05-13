for $x in doc("8-xslt/1-xml.xml")/root/*
where $x/*[local-name() = 'price'] = 200
return $x