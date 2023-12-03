import prisma from "../../../lib/prisma";

export default async function loginUser(req, res) {
    
    const { email, password } = req.body;

    const result = await prisma.user.findFirst({
        where: {
            email: email,
            password: password
        },
    });

    console.log(result);
    res.json(result);
}