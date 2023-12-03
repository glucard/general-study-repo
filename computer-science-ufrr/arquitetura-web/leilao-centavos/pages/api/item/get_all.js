import prisma from "../../../lib/prisma";

export default async function getAll(req, res) {

    const result = await prisma.item.findMany();
    console.log("SDOKAODKASOKD", result);
    res.json(result);

}