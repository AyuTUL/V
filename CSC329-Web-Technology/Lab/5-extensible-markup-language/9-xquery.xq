for $x in doc("8-xslt/1-xml.xml")/root/*
where $x/price = 200
return $x